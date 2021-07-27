#pragma once

#include "main/AppClient.hpp"
#include "shared/AppConfig.hpp"

namespace app
{

class BrowserApp : public CefApp, public CefBrowserProcessHandler
{
public:
    BrowserApp() {}

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;

    void OnBeforeCommandLineProcessing(const CefString &process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;
    void OnContextInitialized() OVERRIDE;

    CefRefPtr<AppClient> getAppClient();

    static CefRefPtr<BrowserApp> sharedHandler();

private:
    IMPLEMENT_REFCOUNTING(BrowserApp);
    DISALLOW_COPY_AND_ASSIGN(BrowserApp);

    CefRefPtr<AppClient> clientInstance;
    static CefRefPtr<BrowserApp> instance;
};

} // namespace app
