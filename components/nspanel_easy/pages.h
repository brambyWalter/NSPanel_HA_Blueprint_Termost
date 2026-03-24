// pages.h

#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <string>
#include "esphome/core/string_ref.h"  // For StringRef

/**
 * @file pages.h
 * Defines constants and functions related to page names for the NSPanel HA Blueprint project.
 */

namespace esphome {
namespace nspanel_easy {

// Constants
/**
 * A compile-time constant array containing the names of pages.
 * These names correspond to various pages of the Nextion TFT file in use,
 * such as settings, home, weather information, and more.
 */
constexpr const char *const page_names[] = {
    "boot",         "home",         "weather01",    "weather02",   "weather03",    "weather04",    "weather05",
    "climate",      "settings",     "screensaver",  "light",       "cover",        "buttonpage01", "buttonpage02",
    "buttonpage03", "buttonpage04", "notification", "qrcode",      "entitypage01", "entitypage02", "entitypage03",
    "entitypage04", "fan",          "alarm",        "keyb_num",    "media_player", "confirm",      "utilities",
    "home_smpl",    "debug",        "water_heater", "theme_apply", "switch"};

constexpr size_t PAGE_COUNT = sizeof(page_names) / sizeof(page_names[0]);
static_assert(PAGE_COUNT <= UINT8_MAX, "PAGE_COUNT exceeds uint8_t range");

// Global system flags - initialized to 0 (all flags false)
extern uint8_t current_page_id;
extern uint8_t last_page_id;
extern uint8_t wakeup_page_id;

/**
 * Compares two null-terminated C-strings at compile time.
 * Equivalent to strcmp(a, b) == 0, but constexpr-compatible.
 * std::strcmp becomes constexpr only in C++23; this works with C++17/20.
 *
 * @param a First null-terminated string.
 * @param b Second null-terminated string.
 * @return true if strings are identical, false otherwise.
 */
constexpr bool page_names_equal(const char *a, const char *b) {
  while (*a && *b) {
    if (*a != *b)
      return false;
    ++a;
    ++b;
  }
  return *a == *b;
}

/**
 * Retrieves the index of a given page name within the page_names array.
 * When called with a string literal, this is resolved entirely at compile time.
 *
 * @param page_name The name of the page to find.
 * @return The index of the page_name in the page_names array, or UINT8_MAX if not found.
 */
constexpr uint8_t get_page_id(const char *page_name) {
  if (page_name == nullptr || *page_name == '\0')
    return UINT8_MAX;
  for (uint8_t i = 0; i < PAGE_COUNT; ++i) {
    if (page_names_equal(page_names[i], page_name))
      return i;
  }
  return UINT8_MAX;
}

/**
 * Retrieves the index of a given page name within the page_names array.
 * Runtime overload for StringRef; cannot be constexpr as StringRef is not a literal type.
 *
 * @param page_name The name of the page to find.
 * @return The index of the page_name in the page_names array, or UINT8_MAX if not found.
 */
inline uint8_t get_page_id(const esphome::StringRef &page_name) {
  if (page_name.empty())
    return UINT8_MAX;
  for (uint8_t i = 0; i < PAGE_COUNT; ++i) {
    if (page_name == page_names[i])
      return i;
  }
  return UINT8_MAX;
}

}  // namespace nspanel_easy
}  // namespace esphome
