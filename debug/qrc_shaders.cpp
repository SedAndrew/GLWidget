/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.8.0
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

  // D:/Qt/7th_semester/lab/OGL_start/GLWidget/fshader.fsh
  
  
    // D:/Qt/7th_semester/lab/OGL_start/GLWidget/vshader.vsh
  
  
  
static const unsigned char qt_resource_data[3974] = { 'Q', 'R', 'C', '_', 'D', 'A', 'T', 'A' };

static const unsigned char qt_resource_name[] = {
  // fshader.fsh
  0x0,0xb,
  0xa,0x1e,0x71,0x78,
  0x0,0x66,
  0x0,0x73,0x0,0x68,0x0,0x61,0x0,0x64,0x0,0x65,0x0,0x72,0x0,0x2e,0x0,0x66,0x0,0x73,0x0,0x68,
    // vshader.vsh
  0x0,0xb,
  0xa,0x3e,0x61,0x78,
  0x0,0x76,
  0x0,0x73,0x0,0x68,0x0,0x61,0x0,0x64,0x0,0x65,0x0,0x72,0x0,0x2e,0x0,0x76,0x0,0x73,0x0,0x68,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/fshader.fsh
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x67,0xa7,0x13,0xd4,0x76,
  // :/vshader.vsh
  0x0,0x0,0x0,0x1c,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0xa,0xfa,
0x0,0x0,0x1,0x67,0xa7,0x18,0x71,0xf3,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_shaders)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_shaders)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x02, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_shaders)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_shaders)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x02, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_shaders)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_shaders)(); }
   } dummy;
}
