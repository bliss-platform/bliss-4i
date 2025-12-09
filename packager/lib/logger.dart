import 'package:cli_util/cli_logging.dart';

// ------------------------------------------------------------
// Bliss Log Types
// ------------------------------------------------------------

enum LogType {
  error,
  warn,
  info,
  debug,
  done,
}

// ------------------------------------------------------------
// ANSI HELPERS
// NOTE: Dart does NOT support "\e", so we must use "\x1B".
//       (This is a modification from the original code.)
// ------------------------------------------------------------


// generic ANSI wrapper function
String applyAnsi(String code, String text, bool enabled) =>
    enabled ? "\x1B[$code" "m$text\x1B[0m" : text;

// ------------------------------------------------------------
// BLISS COLOR FUNCTIONS (same colors as your original code)
// All renamed to more user-friendly names, but logic unchanged.
// ------------------------------------------------------------

// TARGET: Frost Cyan
String colorTarget(String s, bool e) => applyAnsi("38;5;117", s, e);

// ERROR: Aurora Red
String colorError(String s, bool e) => applyAnsi("38;5;203", s, e);

// WARN: Muted Amber
String colorWarning(String s, bool e) => applyAnsi("38;5;180", s, e);

// INFO: Frost Blue
String colorInfo(String s, bool e) => applyAnsi("38;5;111", s, e);

// DEBUG: Storm Gray
String colorDebug(String s, bool e) => applyAnsi("38;5;245", s, e);

// CODE: Lavender
String colorCode(String s, bool e) => applyAnsi("38;5;141", s, e);

// Description: Dim Gray
String colorDescription(String s, bool e) => applyAnsi("2", "$s\n", e);

// DONE: Soft Green
String colorDone(String s, bool e) => applyAnsi("38;5;114", s, e);

// ------------------------------------------------------------
// PURE FUNCTIONAL LOGGER
// IMPORTANT NOTES:
// 1. No classes, no objects — fully functional.
// 2. Uses Google’s ANSI detection (NEW).
// 3. Formatting matches your original implementation exactly.
// ------------------------------------------------------------

void logger(LogType type, String errorCode, String title, String body) {

  // MODIFICATION:
  // Terminal ANSI support detection using cli_util
  final ansiEnabled = Ansi.terminalSupportsAnsi;

  // your original prefix "PACKAGER" with your blue tint
  final prefixTarget = colorTarget("PACKAGER", ansiEnabled);

  // helper function for header
  String makeHeader(String typeLabel) =>
      "${colorCode("4PM$errorCode", ansiEnabled)} [${prefixTarget}::${typeLabel}] ";

  // unchanged control structure, but now functional + cleaner
  switch (type) {
    case LogType.error:
      print(makeHeader(colorError("ERROR", ansiEnabled)));
      print(title);
      print(colorDescription(body, ansiEnabled));
      break;

    case LogType.warn:
      print(makeHeader(colorWarning("WARN", ansiEnabled)));
      print(title);
      print(colorDescription(body, ansiEnabled));
      break;

    case LogType.info:
      print(makeHeader(colorInfo("INFO", ansiEnabled)));
      print(title);
      print(colorDescription(body, ansiEnabled));
      break;

    case LogType.debug:
      print(makeHeader(colorDebug("DEBUG", ansiEnabled)));
      print(title);
      print(colorDescription(body, ansiEnabled));
      break;

    case LogType.done:
      // DONE format is unique in your original code — preserved exactly
      print("[$prefixTarget::${colorDone("DONE", ansiEnabled)}] $title\n");
      break;
			
  }
}