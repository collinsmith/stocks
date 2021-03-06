/**
 * This file contains utility functions to build and manipulate resource paths,
 * as well as precache them.
 */

#include <fakemeta>
#include <file>
#include <logger>

#if defined _precache_stocks_included
  #endinput
#endif
#define _precache_stocks_included

#tryinclude "include/stocks/simple_logger_stocks.inc"
#if !defined _simple_logger_stocks_included
  #include <simple_logger_stocks>
#endif

#tryinclude "include/stocks/exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

#tryinclude "include/stocks/path_stocks.inc"
#if !defined _path_stocks_included
  #include <path_stocks>
#endif

#tryinclude "include/stocks/string_utils.inc"
#if !defined _string_utils_included
  #include <string_utils>
#endif

static const MODELS[] = "models";
static const PLAYER[] = "player";
static const MDL[] = ".mdl";

static const SOUND[] = "sound";

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock BuildPlayerModelPath(dst[], len, const model[]) {
  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException("model cannot be empty!");
    return 0;
  }

  new const maxLen = len;
  len = getPath(dst, len, MODELS, PLAYER, model, model);
  len += copy(dst[len], maxLen - len, MDL);
  return len;
}

stock BuildModelPath(dst[], len, const model[]) {
  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException("model cannot be empty!");
    return 0;
  }

  new const maxLen = len;
  len = getPath(dst, len, MODELS, model);
  len += copy(dst[len], maxLen - len, MDL);
  return len;
}

/**
 * Precaches a given model. Models should begin with {@code "models"}, and
 * typical paths can be constructed using {@link #BuildPlayerModelPath} and
 * {@link #BuildModelPath}.
 * 
 * @param model The path of the model
 * 
 * @return {@code true} if the model was precached, {@code false} otherwise
 * 
 * @throws IllegalArgumentException if {@code model} is empty or does not begin
 *         with "models", or if the model specified by the path does not exist.
 */
stock bool: precacheModel(const model[]) {
#if defined DEBUG_PRECACHING
  logd("Precaching \"%s\"", model);
#endif
  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException("model cannot be empty!");
    return false;
  } else if (stringStartsWith(model, MODELS)) {
    ThrowIllegalArgumentException("model path should start with \"%s\"! (\"%s\")", MODELS, model);
    return false;
  } else if (!file_exists(model)) {
    ThrowIllegalArgumentException("model specified by path \"%s\" does not exist!", model);
    return false;
  }

  engfunc(EngFunc_PrecacheModel, model);
  return true;
}

/**
 * Precaches a given file.
 * 
 * @param file The path to the file
 * 
 * @return {@code true} if the file was precached, {@code false} otherwise
 */
stock bool: precache(const file[]) {
#if defined DEBUG_PRECACHING
  logd("Precaching \"%s\"", file);
#endif
  if (isStringEmpty(file)) {
    ThrowIllegalArgumentException("file cannot be empty!");
    return false;
  } else if (!file_exists(file)) {
    ThrowIllegalArgumentException("file specified by path \"%s\" does not exist!", file);
    return false;
  }

  engfunc(EngFunc_PrecacheGeneric, file);
  return true;
}

/**
 * Precaches a given sound file. Sounds are assumed to be located within the
 * sound directory (i.e., "sound/${sound}").
 * 
 * @param sound Path of the sound
 * 
 * @return {@code true} if the sound was precached, {@code false} otherwise
 */
stock bool: precacheSound(const sound[]) {
  new path[PLATFORM_MAX_PATH];
  getPath(path, charsmax(path), SOUND, sound);
  return precache(path);
}