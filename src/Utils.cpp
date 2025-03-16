#include "Utils.h"

#include <cstdlib>

namespace SWRMemTools {

	unsigned long long ConvertToPartialSeed(std::string fullSeed) {

		std::string partialStr = fullSeed.substr(0, 8);
		return static_cast<unsigned long long>(strtoll(partialStr.c_str(), nullptr, 10));
	}
}