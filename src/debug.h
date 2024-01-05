
// #ifndef DEBUG_H
// #define DEBUG_H

#define debug

#ifdef debug // debug mode
#define DEBUG(x) std::cout << "DEBUG [ file " << __FILE__ << " | line " << __LINE__ << " ]: " << x << std::endl;
#else // release mode
#define DEBUG(x) ;
#endif

// #endif // DEBUG_H