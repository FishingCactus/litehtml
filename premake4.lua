solution "litehtml"

print( _OPTIONS.platform )
    configurations { "release", "debug" }

    if _ACTION ~= "android" and _OPTIONS.platform == nil then
        platforms { "x32", "x64" }
    end
    defines { "LITEHTML_UTF8" }

    targetname "litehtml"
    language "C++"
    kind "StaticLib"

    files
    {
        "src/**.c", "src/**.cpp", "src/**.h"
    }

    configuration "debug"
        defines     { "_DEBUG" }
        flags       { "Symbols" }
        targetsuffix "_d"

    configuration "release"
        defines     { "NDEBUG" }
        flags       { "OptimizeSize" }

    configuration {"windows", "not *android*" }
        defines     { "WIN32" }

    project "litehtml"

        if not os.is("windows") then
            buildoptions { "-std=c++11 -Wno-error=unused-variable -Wno-error=unused-parameter" }
        end

        if androidsdk then androidsdk( 'android-14' ) end
        if androidappabi then androidappabi( "armeabi-v7a" ) end

        configuration "x32"
            targetdir   "bin/i386"

        configuration "x64"
            targetdir   "bin/x64_86"
