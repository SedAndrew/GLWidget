attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;
attribute highp vec3 a_tangent;
attribute highp vec3 a_bitanget;

uniform highp mat4 u_projectionMatrix; // матрица проекций
uniform highp mat4 u_viewMatrix; // видовая матрица
uniform highp mat4 u_modelMatrix; // модельная матрица

uniform highp mat4 u_projectionLightMatrix;
uniform highp mat4 u_shadowLightMatrix;
uniform highp mat4 u_lightMatrix;

uniform highp vec4 u_lightDirection;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp mat3 v_tbnMatrix;
varying highp vec4 v_lightDirection;
varying highp vec4 v_positionLightMatrix;

highp mat3 transpose(in highp mat3 inMatrix) {
    highp vec3 i0 = inMatrix[0];
    highp vec3 i1 = inMatrix[1];
    highp vec3 i2 = inMatrix[2];

    highp mat3 outMatrix = mat3(
          vec3(i0.x, i1.x, i2.x),
          vec3(i0.y, i1.y, i2.y),
          vec3(i0.z, i1.z, i2.z)
          );

    return outMatrix;
}

void main(void)
{
 // модельно видовая матрица
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;

 // формирование конечных координат вершин
 // умножаем матрицу проекции на модельновидовую и на текущие координаты точки
    gl_Position = u_projectionMatrix * mv_matrix * a_position;
 // передача текстурных координат во фрагметный шейдер
    v_texcoord = a_texcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = normalize(a_position);
//    v_position = normalize(mv_matrix * a_position); // прототип normalize

    vec3 tangent   = normalize(vec4(mv_matrix * vec4(a_tangent, 0.0)).xyz);
    vec3 bitangent = normalize(vec4(mv_matrix * vec4(a_bitanget, 0.0)).xyz);
    vec3 normal    = normalize(vec4(mv_matrix * vec4(a_normal, 0.0)).xyz);

    v_tbnMatrix = transpose(mat3(tangent, bitangent, normal));

    v_positionLightMatrix = u_projectionLightMatrix * u_shadowLightMatrix * u_modelMatrix * a_position;
    v_lightDirection = u_lightMatrix * u_lightDirection * u_viewMatrix;
}
