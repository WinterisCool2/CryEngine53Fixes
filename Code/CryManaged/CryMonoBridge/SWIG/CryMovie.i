%include "CryEngine.swig"

%import "CryCommon.i"

%{
#include <CryMovie/IMovieSystem.h>
#include <CryMovie/AnimKey.h>
%}
%feature("director") ITrackEventListener;
%feature("director") IMovieListener;
%typemap(csbase) EAnimParamType "uint"
%typemap(csbase) EAnimCurveType "uint"
%typemap(csbase) EAnimValue "uint"
%csconstvalue("0") eTDT_Void;
%csconstvalue("1") eTDT_Float;
%csconstvalue("2") eTDT_Vec3;
%csconstvalue("3") eTDT_Vec4;
%csconstvalue("4") eTDT_Quat;
%csconstvalue("5") eTDT_Bool;
%include "../../../../CryEngine/CryCommon/CryMovie/IMovieSystem.h"
%include "../../../../CryEngine/CryCommon/CryMovie/AnimKey.h"