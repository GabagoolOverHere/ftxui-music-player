#include "button.hpp"

#include <utility>

using namespace ftxui;

PathButton::PathButton(const char *prefix, const char *title, std::function<void()> on_click)
    : prefix_(prefix), title_(title), on_click_(std::move(on_click)) {}

Element PathButton::Render() {
    auto style = Focused() ? (Decorator(inverted) | focus) : nothing;
    return hbox({
                    text(prefix_),
                    text(title_) | style | color(Color::GrayDark) | reflect(box_),
                });
}
