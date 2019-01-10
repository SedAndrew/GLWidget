struct materialProperty
{
    vec3 diffuseColor;
    vec3 ambienceColor;
    vec3 specularColor;
    float shininess;
};

struct FogInfo
{
    float maxDist;
    float minDist;
    vec4 color;
};

uniform sampler2D u_diffuseMap;
uniform sampler2D u_normalMap;
uniform sampler2D u_shadowMap;

uniform highp float u_lightPower; // сила источника света

uniform materialProperty u_materialProperty;
uniform bool u_isUsingDiffuseMap;
uniform bool u_isUsingNormalMap;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp mat3 v_tbnMatrix;

varying highp vec4 v_lightDirection;
varying highp vec4 v_positionLightMatrix;

float SampleShadowMap(sampler2D map, vec2 coords, float compare)
{
    vec4 v = texture2D(map, coords);//передаём карту и координаты
    float value = v.x * 255.0 + (v.y * 255.0 + (v.z * 255.0 +v.w)/255.0) / 255.0;//Извлекаем значение
    return step(compare, value);//Функция сравнивает два значения, возвращает 1 или 0, 1 если compare будет больше
}

float SampleShadowMapLinear(sampler2D map, vec2 coords, float compare, vec2 texelSize)
{
    //texel - размер пикселя в текстурных координатах
    vec2 pixelPos = coords / texelSize + 0.5;//Получаем позицию пикселя, она рассчитывается как координаты. +0.5 чтобы попасть в центр пикселя
    vec2 fractPart = fract(pixelPos);//Получаем дробную часть от пикселя
    vec2 startTexel = (pixelPos - fractPart) * texelSize;//переходим в текстурные координаты

    //Находим приближение по 4-ём соседним клеткам
    float blTexel = SampleShadowMap(map, startTexel, compare);
    float brTexel = SampleShadowMap(map, startTexel + vec2(texelSize.x, 0.0), compare);
    float tlTexel = SampleShadowMap(map, startTexel + vec2(0.0, texelSize.y), compare);
    float trTexel = SampleShadowMap(map, startTexel + texelSize, compare);

    //Текстурные координаты начинаются всегда с левого нижнего угла

    //Используя функцию микс найдём интерполяцию от одной точки, до другой с учётом fractPart
    float mixA = mix(blTexel, tlTexel, fractPart.y);
    float mixB = mix(brTexel, trTexel, fractPart.y);

    return mix(mixA, mixB, fractPart.x);
}

float SampleShadowMapPCF(sampler2D map, vec2 coords, float compare, vec2 texelSize)
{
    float result = 0.0;
    for (float y = -1.0; y < 1.0; y += 1.0)//Можно поменять, но упрётся в производительность
        for (float x = -1.0; x < 1.0; x += 1.0)
        {
            vec2 offset = vec2(x, y) * texelSize;//Отклонение от центрального
            //Берём каждый пиксель и от него отклоняемся во все стороны по одному и усредняем значения всех вокруг пикселей
            result += SampleShadowMapLinear(map, coords + offset, compare, texelSize);//Применяем линейную фильтраци для каждого из элементов
        }

    return result / 9.0; //Так как ровно 9 элементов
}

float CalcShadowAmount(sampler2D map, vec4 initialShadowCoords)
{
    //Преобразуем к нужному диапозону
    vec3 tmp = v_positionLightMatrix.xyz / v_positionLightMatrix.w;//Приведёт к диапозону от -1 до 1
    tmp = tmp * vec3(0.5) + vec3(0.5);
    float offset = 2.0;
    // dot(v_normal, v_lightDirection.xyz);//солнце на текущую нормаль
    offset *= dot(v_normal, v_lightDirection.xyz);;//if (d < 0)//Значит точно в тени находится

    return SampleShadowMapPCF(u_shadowMap, tmp.xy, tmp.z * 255.0 + offset, vec2(1.0 / 1024));//tmp.z - это удалённость
    //Меняя значени после 255.0 также меняется качество тени, но могут появлятся белые полосы
}

void main(void)
{
   highp float shadowCoef = CalcShadowAmount(u_shadowMap, v_positionLightMatrix);

  // результирующий цвет (черный)
   vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
   vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
   vec4 diffMatColor = texture2D(u_diffuseMap, v_texcoord);
   vec3 usingNormal = v_normal;
   if (u_isUsingNormalMap)
    usingNormal = normalize(texture2D(u_normalMap, v_texcoord).rgb * 2.0 - 1.0);
  // вектор направления взгляда
   vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
   if (u_isUsingNormalMap)
    eyeVect = normalize(v_tbnMatrix * eyeVect);
  // вектор цвета (из точки 0,0,0 в точку, которую в данный момент обрабатывает фрагментный шейдер)
   vec3 lightVect = normalize(v_lightDirection.xyz);
   if (u_isUsingNormalMap)
    lightVect = normalize(v_tbnMatrix * lightVect);
  // отраженный свет (вектор направленный из точки которую мы рассматриваем в направлении куда отразится этот свет)
   vec3 reflectLight = normalize(reflect(lightVect, usingNormal));
  // длина вектора от наблюдателя до рассматриваемой точки
   float len = length(v_position.xyz - eyePosition.xyz);
  // specularFactor - отвечает за то, на сколько большим будет пятно блика
   float specularFactor = u_materialProperty.shininess;
  // ambientFactor - отвечает за то, насколько ярким будет материал
   float ambientFactor = 0.1;


   if (u_isUsingDiffuseMap == false) diffMatColor = vec4(u_materialProperty.diffuseColor, 1.0); // не прозрачный
   // добавление диффузного освещения
   vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(usingNormal, -lightVect));// / (1 + 0.75 * pow(len, 2));
   resultColor += diffColor;
   // добавление ambient освещения
   vec4 ambientColor = ambientFactor * diffMatColor;
   resultColor += ambientColor * vec4(u_materialProperty.ambienceColor, 1.0);
   // добаление бликов
   vec4 specularColor = vec4(0.96, 0.96, 0.73, 1.0) * u_lightPower * pow(max(0, dot(reflectLight, -eyeVect)), specularFactor);// / (1 + 0.75 * pow(len, 2));
   resultColor += specularColor * vec4(u_materialProperty.specularColor, 1.0);

   shadowCoef += 0.15;//Влияет на яркость тени
   if (shadowCoef > 1.0) shadowCoef = 1.0;

   resultColor *= shadowCoef;

   FogInfo Fog;
   Fog.color = vec4(0.16, 0.07, 0.15, 1.0);
   Fog.maxDist = -0.02;
   Fog.minDist = 0.06;
   float LOG28 = 1.447158;
   float z = gl_FragCoord.z / gl_FragCoord.w;
   float fogFactor = exp2( Fog.maxDist * Fog.minDist * z * z * LOG28);
   fogFactor = clamp(fogFactor, 0.0, 1.0);

   resultColor = mix(Fog.color, resultColor, fogFactor);

   gl_FragColor = resultColor;
//    gl_FragColor = vec4(0.2, 0.93, 0.25, 0.2);
//    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
