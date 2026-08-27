# ============================================================
# RPG-To-Do-List Makefile
# ============================================================

# ------------------------------------------------------------
# Compiler / Flags
# ------------------------------------------------------------

CC := gcc

CFLAGS := -std=c99 -Wall -Wextra -fPIC	-Wunused-label
CPPFLAGS := -Iinclude -Iconfig

LDFLAGS :=
LDLIBS := -ldl


# ------------------------------------------------------------
# Project directories
# ------------------------------------------------------------

LIBNAME := general
LIBDIR := lib

SRCDIR := core
BUILDDIR := build

PLUGIN_SRC_DIR := plugin_src
PLUGIN_OUT_DIR := database/do-not-change-these/plugins

USER_DIR := database/users
AUTO_LOGIN := database/do-not-change-these/auto-login.txt


# ------------------------------------------------------------
# Main executable
# ------------------------------------------------------------

CORE_SRCS := main.c
TARGET := rpg


# ------------------------------------------------------------
# General dynamic library
#
# core/general_funcs.c
#       ↓
# lib/libgeneral.so
# ------------------------------------------------------------

GENERAL_SRC := $(SRCDIR)/general_funcs.c
GENERAL_OBJ := $(BUILDDIR)/general_funcs.o
GENERAL_LIB := $(LIBDIR)/lib$(LIBNAME).so


# ------------------------------------------------------------
# Plugins
# ------------------------------------------------------------

PLUGIN_DIRS := $(wildcard $(PLUGIN_SRC_DIR)/*)

PLUGIN_SOS := \
	$(patsubst $(PLUGIN_SRC_DIR)/%, \
	$(PLUGIN_OUT_DIR)/%.so, \
	$(PLUGIN_DIRS))


# ------------------------------------------------------------
# Operating system
# ------------------------------------------------------------

ifeq ($(OS),Windows_NT)

	TARGET := rpg.exe

	MKDIR_CMD := if not exist "database\users" mkdir "database\users"

	RM_CMD := del /Q /F $(TARGET) rpg.bat 2>nul || true

else

	TARGET := rpg

	MKDIR_CMD := mkdir -p $(USER_DIR)

	RM_CMD := rm -f $(TARGET) rpg_launcher

endif


# ------------------------------------------------------------
# Phony targets
# ------------------------------------------------------------

.PHONY: all clean install uninstall directories plugins update-plugins


# ============================================================
# ALL
# ============================================================

all: directories $(GENERAL_LIB) $(TARGET) plugins update-plugins


# ============================================================
# DIRECTORIES
# ============================================================

directories:
	@$(MKDIR_CMD)
	@mkdir -p $(PLUGIN_OUT_DIR)
	@mkdir -p $(LIBDIR)
	@mkdir -p $(BUILDDIR)


# ============================================================
# GENERAL DYNAMIC LIBRARY
# ============================================================

$(GENERAL_LIB): $(GENERAL_OBJ)
	@echo "Building general dynamic library: $@"
	@$(CC) -shared -Wl,-soname,lib$(LIBNAME).so -o $@ $^


# ------------------------------------------------------------
# Compile general_funcs.c
# ------------------------------------------------------------

$(GENERAL_OBJ): $(GENERAL_SRC)
	@mkdir -p $(BUILDDIR)
	@echo "Compiling shared library source: $<"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


# ============================================================
# MAIN PROGRAM
# ============================================================

$(TARGET): $(CORE_SRCS) $(GENERAL_LIB)
	@echo "Building main program: $(TARGET)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(CORE_SRCS) \
		-L$(LIBDIR) \
		-l$(LIBNAME) \
		-Wl,-rpath,'$$ORIGIN/$(LIBDIR)' \
		-o $(TARGET) \
		$(LDFLAGS) $(LDLIBS)


# ============================================================
# PLUGINS
# ============================================================

$(PLUGIN_OUT_DIR)/%.so: $(PLUGIN_SRC_DIR)/%
	@echo "Building plugin: $(@F)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -shared \
		$(wildcard $</*.c \
			$</*/*.c \
			$</*/*/*.c \
			$</*/*/*/*.c) \
		-L$(LIBDIR) \
		-l$(LIBNAME) \
		-Wl,-rpath,'$$ORIGIN/../../../$(LIBDIR)' \
		-o $@ \
		$(shell cat $</flags.txt 2>/dev/null || echo "")


# ============================================================
# PLUGIN COLLECTION
# ============================================================

plugins: $(PLUGIN_SOS)


# ============================================================
# UPDATE AVAILABLE PLUGINS
# ============================================================

update-plugins:
	@echo "Updating available plugin list..."
	@ls -1 $(PLUGIN_OUT_DIR)/*.so > \
		database/do-not-change-these/plugins/available_plugins.txt \
		2>/dev/null || true


# ============================================================
# INSTALL / UNINSTALL
# ============================================================

ifeq ($(OS),Windows_NT)

install: all
	@echo @echo off > rpg.bat
	@echo cd /d "$(CURDIR)" >> rpg.bat
	@echo $(TARGET) %%* >> rpg.bat
	@echo "Installing system-wide (Administrator privileges may be required)..."
	@copy /Y rpg.bat "C:\Windows\rpg.bat" >nul || \
		(echo ERROR: Access to C:\Windows was denied. Please run the terminal as Administrator! && exit 1)
	@echo "Installation successful! You can now run 'rpg' from any terminal."


uninstall:
	@echo "Removing from system..."
	@del /Q /F "C:\Windows\rpg.bat" 2>nul || \
		(echo ERROR: Please run the terminal as Administrator to uninstall! && exit 1)
	@echo "Uninstallation completed. You can manually remove the .exe from the project directory."

else

install: all
	@echo "Installing system-wide..."
	@echo '#!/bin/bash' > rpg_launcher
	@echo 'cd "$(CURDIR)" && ./$(TARGET) "$$@"' >> rpg_launcher
	@chmod +x rpg_launcher
	@sudo mv rpg_launcher /usr/local/bin/$(TARGET)
	@sudo mkdir -p /usr/local/share/man/man1
	@sudo cp rpg.1 /usr/local/share/man/man1/
	@sudo gzip -f /usr/local/share/man/man1/rpg.1
	@sudo mandb -q
	@echo "Installation successful! Run 'rpg' to start the application or 'man rpg' to view the manual."


uninstall:
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstallation completed."

endif


# ============================================================
# CLEAN
# ============================================================

clean:
	@$(RM_CMD)
	@rm -f $(GENERAL_OBJ)
	@rm -f $(GENERAL_LIB)
	@rm -f $(PLUGIN_OUT_DIR)/*.so
	@rm -rf $(BUILDDIR)
	@rm -rf $(USER_DIR)
	@rm -rf $(AUTO_LOGIN)
	@echo "Cleanup completed."
