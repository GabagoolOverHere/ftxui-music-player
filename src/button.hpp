
#ifndef FTXUI_STARTER_BUTTON_HPP
#define FTXUI_STARTER_BUTTON_HPP

#include <functional>

#include <ftxui/component/component.hpp>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

class PathButton : public ComponentBase {
public:
    PathButton(const char *prefix, const char *title, std::function<void()> on_click);
    Element Render() override;

private:
    std::function<void()> on_click_;
    const char *prefix_;
    const char *title_;
    Box box_;
};

#endif //FTXUI_STARTER_BUTTON_HPP
