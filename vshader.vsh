attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;

uniform highp mat4 u_projectionMatrix; // матрица проекций
uniform highp mat4 u_viewMatrix; // видовая матрица
uniform highp mat4 u_modelMatrix; // модельная матрица

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

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


}
