struct materialProperty
{
    vec3 diffuseColor;
    vec3 ambienceColor;
    vec3 specularColor;
    float shininess;
};

uniform sampler2D u_diffuseMap;
uniform sampler2D u_normalMap;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower; // сила источника света

uniform materialProperty u_materialProperty;
uniform bool u_isUsingDiffuseMap;
uniform bool u_isUsingNormalMap;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp mat3 v_tbnMatrix;

struct FogInfo
{
    float maxDist;
    float minDist;
    vec4 color;
};

uniform FogInfo Fog;

void main(void)
{
  // результирующий цвет (черный)
   vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
   vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
  // диффузный цвет материала
   vec4 diffMatColor = texture2D(u_diffuseMap, v_texcoord);
  // вектор напроавления взгляда
   vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
  // вектор цвета (из точки 0,0,0 в точку, которую в данный момент обрабатывает фрагментный шейдер)
   vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
  // отраженный свет (вектор направленный из точки которую мы рассматриваем в направлении куда отразится этот свет)
   vec3 reflectLight = normalize(reflect(lightVect, v_normal));
  // длина вектора от наблюдателя до рассматриваемой точки
   float len = length(v_position.xyz - eyePosition.xyz);
  // specularFactor - отвечает за то, на сколько большим будет пятно блика
   float specularFactor = u_materialProperty.shininess;
  // ambientFactor - отвечает за то, насколько ярким будет материал
   float ambientFactor = 0.1;


   if (u_isUsingDiffuseMap == false) diffMatColor = vec4(u_materialProperty.diffuseColor, 1.0); // не прозрачный
   // добавление диффузного освещения
   vec4 diffColor = diffMatColor * u_lightPower * max(0,dot(v_normal, -lightVect));// / (1 + 0.75 * pow(len, 2));
   resultColor += diffColor;
   // добавление ambient освещения
   vec4 ambientColor = ambientFactor * diffMatColor;
   resultColor += ambientColor * vec4(u_materialProperty.ambienceColor, 1.0);
   // добаление бликов
   vec4 specularColor = vec4(0.96, 0.96, 0.73, 1.0) * u_lightPower * pow(max(0, dot(reflectLight, -eyeVect)), specularFactor);// / (1 + 0.75 * pow(len, 2));
   resultColor += specularColor * vec4(u_materialProperty.specularColor, 1.0);


   Fog.color = vec4(0.16, 0.07, 0.15, 1.0);
   Fog.maxDist = -0.06;
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
