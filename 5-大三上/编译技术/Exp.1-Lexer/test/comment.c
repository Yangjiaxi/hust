/* First allocation is just for 2 elements, since we don't know if this *
 * scanner will even need a stack. We use 2 instead of 1 to avoid an *
 * immediate realloc on the next call.*
 */

// Inline Comment