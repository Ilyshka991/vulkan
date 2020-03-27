#include "common/logging.h"
#include "platform/platform.h"
#include "hello_triangle.h"

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#	include "platform/android/android_platform.h"
void android_main(android_app *state)
{
    vkb::AndroidPlatform platform{state};
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
#	include "platform/windows/windows_platform.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     PSTR lpCmdLine, INT nCmdShow)
{
    vkb::WindowsPlatform platform{hInstance, hPrevInstance,
                                  lpCmdLine, nCmdShow};
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
#	include "platform/unix/unix_d2d_platform.h"
int main(int argc, char *argv[])
{
    vkb::UnixD2DPlatform platform{argc, argv};
#else
#   include "platform/unix/unix_platform.h"
int main(int argc, char *argv[]) {
#	if defined(VK_USE_PLATFORM_MACOS_MVK)
    vkb::UnixPlatform platform{vkb::UnixType::Mac, argc, argv};
#	elif defined(VK_USE_PLATFORM_XCB_KHR)
    vkb::UnixPlatform platform{vkb::UnixType::Linux, argc, argv};
#	endif
#endif

    vkb::Platform::set_external_storage_directory("/Users/ilyapechuro/Projects/Vulkan test/");

    try {
        auto app = create_hello_triangle();
        app->set_name("Vulkan Samples");
        app->parse_options(platform.get_arguments());
        if (platform.initialize(std::move(app))) {
            platform.main_loop();
            platform.terminate(vkb::ExitCode::Success);
        } else {
            platform.terminate(vkb::ExitCode::UnableToRun);
        }
    } catch (const std::exception &e) {
        LOGE(e.what())
        platform.terminate(vkb::ExitCode::FatalError);
    }

#ifndef VK_USE_PLATFORM_ANDROID_KHR
    return EXIT_SUCCESS;
#endif
}
