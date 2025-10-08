#ifndef OPTOR_SOURCE_COMMON_INCLUDE_COMMON_ERROR_HANDLER_HPP
#define OPTOR_SOURCE_COMMON_INCLUDE_COMMON_ERROR_HANDLER_HPP

#include <iostream>
#include <functional>
#include <source_location>

#include "Concole.hpp"

namespace Common
{
    
class ErrorHandler {
    public:
        template<typename Func, typename... Args>
        static std::invoke_result_t<Func, Args...> ExecuteWithHandling(
            const std::source_location location,
            Func&& func, 
            Args&&... args) {
            try {
                if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>){
                    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                    return 0;
                } else {
                    return std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                }
            } catch (const std::exception& e) {
                HandleException(e, location);
                throw; 
            }
        }

    private:
        static void HandleException(const std::exception& e, 
                                    const std::source_location& location) {
            std::cerr << RED_FORMAT
                << "Error at " << location.file_name() 
                << ":" << location.line() 
                << " in " << location.function_name() 
                << YELLOW_FORMAT
                << "\nMessage: '" 
                << NORMAL_FORMAT 
                << e.what() 
                << YELLOW_FORMAT 
                << "'"
                << NORMAL_FORMAT 
                << "\n";
        }
};

#define ERROR_HANDLE(func, ...) \
    Common::ErrorHandler::ExecuteWithHandling(std::source_location::current(), func, ##__VA_ARGS__)


}

#endif /*OPTOR_SOURCE_COMMON_INCLUDE_COMMON_ERROR_HANDLER_HPP*/