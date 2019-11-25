static void yyensure_buffer_stack(void)
{
    yy_size_t num_to_alloc;

    if (!(yy_buffer_stack))
    {
        /* First allocation is just for 2 elements, since we don't know if this
         * scanner will even need a stack. We use 2 instead of 1 to avoid an
         * immediate realloc on the next call.
         */
        num_to_alloc = 1;
        (yy_buffer_stack) = (struct yy_buffer_state**)yyalloc(
            num_to_alloc * sizeof(struct yy_buffer_state*));
        if (!(yy_buffer_stack))
            YY_FATAL_ERROR("out of dynamic memory in yyensure_buffer_stack()");

        memset((yy_buffer_stack), 0,
               num_to_alloc * sizeof(struct yy_buffer_state*));

        (yy_buffer_stack_max) = num_to_alloc;
        (yy_buffer_stack_top) = 0;
        return;
    }

    if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1)
    {
        /* Increase the buffer to prepare for a possible push. */
        int grow_size = 8 /* arbitrary grow size */;

        num_to_alloc = (yy_buffer_stack_max) + grow_size;
        (yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc(
            (yy_buffer_stack), num_to_alloc * sizeof(struct yy_buffer_state*));
        if (!(yy_buffer_stack))
            YY_FATAL_ERROR("out of dynamic memory in yyensure_buffer_stack()");

        /* zero only the new slots.*/
        memset((yy_buffer_stack) + (yy_buffer_stack_max), 0,
               grow_size * sizeof(struct yy_buffer_state*));
        (yy_buffer_stack_max) = num_to_alloc;
    }
}