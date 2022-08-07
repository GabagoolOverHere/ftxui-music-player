#include <memory>  // for shared_ptr, allocator, __shared_ptr_access

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include <functional>  // for function
#include <iostream>  // for basic_ostream::operator<<, operator<<, endl, basic_ostream, basic_ostream<>::__ostream_type, cout, ostream
#include <string>    // for string, basic_string, allocator
#include <vector>
#include <filesystem>

using namespace ftxui;


int main(int argc, const char *argv[]) {
    auto screen = ScreenInteractive::Fullscreen();

    std::string button_label = "OK";
    std::function<void()> on_button_clicked_;

    std::vector<std::string> tab_values{
        "songs",
        "animations"
    };
    int tab_selected = 0;
    auto tab_toggle = Toggle(&tab_values, &tab_selected);

    std::vector<std::string> tab_1_entries;
    std::vector<std::string> tab_2_entries{
        "rick ashley",
        "snoop dogg",
        "technoviking"
    };
    int tab_1_selected = 0;
    int tab_2_selected = 0;

    auto tab_container = Container::Tab({
            Menu(&tab_1_entries, &tab_1_selected),
            Radiobox(&tab_2_entries, &tab_2_selected),
        },
        &tab_selected);
    auto tabs = Container::Vertical({
        tab_toggle,
        tab_container,
    });

    std::string file_path;

    std::function<void()> scan_path = [&file_path, &tab_1_entries]() {
        std::vector<std::string> ext{".m4a", ".mp3", ".wave"};
        if (std::filesystem::is_directory(file_path) && !std::filesystem::is_empty(file_path))
            for (const auto &entry: std::filesystem::directory_iterator(file_path))
                if (std::filesystem::is_regular_file(entry) &&
                    std::find(begin(ext), end(ext), std::filesystem::path(entry).extension()) != std::end(ext))
                    tab_1_entries.push_back(std::filesystem::path(entry).filename());
    };

    Component input_file_path = Input(&file_path, "");
    auto button = Button(&button_label, scan_path);
    auto file_input = Container::Vertical({
        input_file_path,
        button
    });

    auto middle = Renderer(file_input, [&] {
        return vbox(
            text("Undefined music folder. Please, enter the path :"),
            input_file_path->Render(),
            button->Render()
        ) | center;
    });
    auto bottom = Renderer([] { return text("bottom") | center; });

    int left_size = 40;
    int bottom_size = 2;

    auto container = middle;
    container = ResizableSplitLeft(tabs, container, &left_size);
    container = ResizableSplitBottom(bottom, container, &bottom_size);

    auto renderer =
        Renderer(container, [&] { return container->Render() | border; });

    screen.Loop(renderer);
}