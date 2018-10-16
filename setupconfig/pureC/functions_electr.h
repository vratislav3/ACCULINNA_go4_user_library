#ifndef FUNCTIONS_ELECTR_H
#define FUNCTIONS_ELECTR_H

#include "structs_electr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================= */
/* stc_elblock ================================================================================= */
/* ============================================================================================= */

/**
 * Reset all the fields.
 */
void InitStcElblock(stc_elblock* ptr);

/* ============================================================================================= */
/* stc_electr_chars ============================================================================ */
/* ============================================================================================= */

/**
 *
 */
void InitStcElectrChars(stc_electr_chars* ptr);

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_ELECTR_H */
