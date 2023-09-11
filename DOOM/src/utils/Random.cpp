#include "utils/Random.hpp"
#include <cstdlib>
#include <ctime>

namespace Doom {
    namespace Random {
        /**
         * Avoid reinitializing.
         */
        static bool IsInitialized = false ;

        void Initialize(const bool force) {
            if (!IsInitialized || force) {
                auto seed = static_cast<unsigned int>(time(nullptr)) ;
                srand(seed) ;
                IsInitialized = true ;
            }
        }

        int GetInteger() {
            return rand() ;
        }

        int GetInteger(const int min, const int max) {
            if (min >= max) {
                return 0 ;
            }

            int diff = max - min ;
            int random = (rand() % diff) + min ;
            return random ;
        }

        float GetNormalizedFloat() {
            const float MaxRandom = RAND_MAX ;
            float random = static_cast<float>(rand()) ;
            return random / MaxRandom ;
        }
    }
}
