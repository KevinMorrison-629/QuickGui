#include "quickgui/quickgui.h"
#include <iostream>

// Helper function to create a row in our simulated table, reducing code duplication.
std::unique_ptr<QGUI::Frame> create_quote_row(const std::string &id, const std::string &stage, const std::string &status,
                                              const std::string &ef_date, const std::string &exp_date,
                                              const std::string &insured)
{
    // Each row is a horizontal frame. We give it an invisible title by using "##".
    auto row = std::make_unique<QGUI::Frame>("##" + id, QGUI::LayoutDirection::Horizontal);

    // To simulate columns, we can wrap each item in a fixed-size, invisible frame.
    // This is a more advanced technique. For simplicity now, we'll just add the elements.
    // NOTE: Without fixed-size columns, the alignment won't be perfect like a real table.

    row->add_element(std::make_unique<QGUI::Button>("Actions"));
    row->add_element(std::make_unique<QGUI::Spacer>(10.0f));
    row->add_element(std::make_unique<QGUI::Text>(id, 1.0f));
    row->add_element(std::make_unique<QGUI::Spacer>(20.0f));
    row->add_element(std::make_unique<QGUI::Text>(stage, 1.0f));
    row->add_element(std::make_unique<QGUI::Spacer>(20.0f));
    row->add_element(std::make_unique<QGUI::Button>(status));
    row->add_element(std::make_unique<QGUI::Spacer>(20.0f));
    row->add_element(std::make_unique<QGUI::Text>(ef_date));
    row->add_element(std::make_unique<QGUI::Spacer>(20.0f));
    row->add_element(std::make_unique<QGUI::Text>(exp_date));
    row->add_element(std::make_unique<QGUI::Spacer>(20.0f));
    row->add_element(std::make_unique<QGUI::Text>(insured));

    return row;
}

int main()
{
    // Initialize the library (starts GLFW)
    if (!QGUI::init())
    {
        return -1;
    }

    try
    {
        // Main application window
        QGUI::Window app_window("Plovdiv CRM", 1600, 900);

        // --- 1. Top Bar ---
        // A frame aligned to the top, acting as the main header.
        auto top_bar = std::make_unique<QGUI::Frame>("##TopBar", QGUI::LayoutDirection::Horizontal, 1.0f);
        top_bar->add_element(std::make_unique<QGUI::Text>("Plovdiv", 1.0f));
        top_bar->add_element(std::make_unique<QGUI::Spacer>(3.0f));
        top_bar->add_element(std::make_unique<QGUI::Button>("NowCerts Update: 04/21/20.0f22. View Details", 1.0f));
        // We would add more elements and a spring/spacer to push the right-side items.
        app_window.add_frame(std::move(top_bar));

        // --- 2. Left Sidebar ---
        // A frame aligned to the left for navigation.
        auto sidebar = std::make_unique<QGUI::Frame>("##Sidebar", QGUI::LayoutDirection::Vertical, 1.5f);
        sidebar->add_element(std::make_unique<QGUI::Button>("Call Logs", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Insureds", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Prospects", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Prospects/Leads", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Opportunities", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Quotes/Submissions", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("Quote Applications", 1.0f));
        sidebar->add_element(std::make_unique<QGUI::Text>("PIPELINES", 4.0f));
        sidebar->add_element(std::make_unique<QGUI::Button>("PIPELINES", 2.0f));
        // ...and so on for the rest of the sidebar items.
        app_window.add_frame(std::move(sidebar));

        // --- 3. Main Content Area ---
        // A floating frame that the user can position in the remaining space.
        auto main_content = std::make_unique<QGUI::Frame>("Main Content", QGUI::LayoutDirection::Vertical);

        // 3a. Filters Section
        auto filters = std::make_unique<QGUI::Frame>("QUOTES", QGUI::LayoutDirection::Vertical);

        auto filter_row1 = std::make_unique<QGUI::Frame>("##filter_row1", QGUI::LayoutDirection::Horizontal);
        filter_row1->add_element(std::make_unique<QGUI::Text>("Zip Code"));
        filter_row1->add_element(std::make_unique<QGUI::Button>("[Please Choose]"));
        filter_row1->add_element(std::make_unique<QGUI::Spacer>(5.0f));
        filter_row1->add_element(std::make_unique<QGUI::Text>("Tag"));
        filter_row1->add_element(std::make_unique<QGUI::Button>("[Please Choose]"));
        filters->add_element(std::move(filter_row1));
        filters->add_element(std::make_unique<QGUI::Button>("Search"));

        main_content->add_element(std::move(filters));

        // 3b. Quotes List Section
        auto quotes_list = std::make_unique<QGUI::Frame>("QUOTES LIST", QGUI::LayoutDirection::Vertical);

        // Header for the list with an "Add New" button
        auto list_header = std::make_unique<QGUI::Frame>("##list_header", QGUI::LayoutDirection::Horizontal);
        list_header->add_element(std::make_unique<QGUI::Button>("+ Add New"));
        quotes_list->add_element(std::move(list_header));

        // Add a header row for the table
        quotes_list->add_element(create_quote_row("Quote Id", "Quote Stage", "Status", "Ef. Date", "Exp. Date", "Insured"));
        quotes_list->add_element(std::make_unique<QGUI::Spacer>(5.0f)); // A little vertical space

        // Add the data rows using our helper function
        quotes_list->add_element(create_quote_row("QT_015BAAR4YS1", "Presented", "Expired", "04/01/20.0f23",
                                                  "10.0f/05/20.0f21", "Hartford Account"));
        quotes_list->add_element(
            create_quote_row("QT_015BAAR4YS1", "---", "Active", "04/01/20.0f23", "04/01/20.0f24", "Hartford Account"));
        quotes_list->add_element(
            create_quote_row("QT_121212121_Cloned", "---", "Expired", "01/03/20.0f23", "01/12/20.0f22", "1 Oxcorp1234"));
        quotes_list->add_element(
            create_quote_row("QT_121212121", "---", "Active", "01/03/20.0f23", "01/03/20.0f24", "1 Oxcorp1234"));

        main_content->add_element(std::move(quotes_list));

        app_window.add_frame(std::move(main_content));

        // --- Run Application ---
        app_window.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        QGUI::shutdown();
        return -1;
    }

    // Clean up resources
    QGUI::shutdown();
    return 0;
}
