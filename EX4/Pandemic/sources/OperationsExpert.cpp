#include "OperationsExpert.hpp"

namespace pandemic{
    OperationsExpert& OperationsExpert::build(){
        _board.add_research(_city);
        return *this;
    }
}