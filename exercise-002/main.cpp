#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More information at https://github.com/CLIUtils/CLI11#usage
     */
    // Möglichkeit, -V oder --version einzugeben, um Versionsinformationen anzuzeigen
    CLI::App app{PROJECT_NAME};
    //Initialisierung count
    int count = 20;
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        //Möglichkeit, -c oder --count einzugeben, um Parameter count zu übergeben
        app.add_option("-c,--count", count, fmt::format("Create a vector with the given size default: {}", count));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }
    //Vektor erstellen mit Anzahl Elemente durch count vorgegeben
    std::vector<int> data(count);

    for (int i = 0; i < count; i++)
    {
        data[i] = std::rand() % 101;
    }

    //Ausgabetext
    fmt::print("Created a vector with {} elements", count);
    fmt::print("Created this vector: {}", fmt::join(data, ", "));

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */

    return 0; /* exit gracefully*/
}
