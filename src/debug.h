#ifndef FEATHER_DEBUG_H
#define FEATHER_DEBUG_H

/* debug printing */
#ifdef FEATHER_DEBUG
#define FEATHER_DBG_PRINT(x) printf x
#else
#define FEATHER_DBG_PRINT(x) do{} while (0)
#endif

#endif
