################################################################################
# Automatically-generated file.  Do not edit directly; use project properties.
################################################################################


com.palmsource.eclipse.palmos4dev.compiler.m68k_palmos_C_SRCS += \
${addprefix $(ROOT)/src/, \
MathLib.c \
ai.c \
bullet.c \
draw.c \
formh_game.c \
formh_main.c \
formh_newgame.c \
formh_options.c \
main.c \
ui.c \
utilities.c \
}

src/%.o: $(ROOT)/src/%.c
	@echo
	m68k-palmos-gcc -c -D__PALMOS__=0x05000000 -I"$(TOOLS_DIR)include/stlport" -O0 -g -fexceptions -UNDEBUG $(subst sdk-,-palmos,$(SDK_VERSION)) -o $@  $<
	echo -n $(@:%.o=%.d) 'src/' > $(@:%.o=%.d) && \
	m68k-palmos-gcc -c -MM -MG -P -w -D__PALMOS__=0x05000000 -I"$(TOOLS_DIR)include/stlport" -O0 -g -fexceptions -UNDEBUG $(subst sdk-,-palmos,$(SDK_VERSION))  $< >> $(@:%.o=%.d)


