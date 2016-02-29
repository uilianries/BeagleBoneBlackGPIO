#ifndef BBB_GPIO_DEFINITION_HPP_
#define BBB_GPIO_DEFINITION_HPP_

#include <string>

namespace bbb {
namespace gpio {

    static const unsigned index_max = 115;
    static const std::string gpio_class_path = "/sys/class/gpio";
    static const std::string gpio_dir_prefix = "gpio";
    static const std::string export_file_name = "export";
    static const std::string unexport_file_name = "unexport";
    static const std::string value_file_name = "value";
    static const std::string direction_file_name = "direction";

    enum class pin_level : int { low,
                                 high };

    enum class stream_direction : int { input,
                                        output,
                                        bidirectional };
}
}

#endif // BBB_GPIO_DEFINITION_HPP_
