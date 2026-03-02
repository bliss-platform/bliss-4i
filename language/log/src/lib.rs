//General bliss log crate implemented as per
//https://bliss-platform.github.io/bliss-4i/articles/log-convention.html#_7-separation-of-logs-and-output

// ANSI color codes per spec
const COLOR_TARGET: &str = "\x1b[38;5;117m";
const COLOR_ERROR: &str = "\x1b[38;5;203m";
const COLOR_WARN: &str = "\x1b[38;5;180m";
const COLOR_INFO: &str = "\x1b[38;5;111m";
const COLOR_DEBUG: &str = "\x1b[38;5;245m";
const COLOR_CODE: &str = "\x1b[38;5;141m";
const COLOR_DESC: &str = "\x1b[2m";
const COLOR_DONE: &str = "\x1b[38;5;114m";
const COLOR_RESET: &str = "\x1b[0m";

pub enum LogLayout {
    General {
        title: String,
        message: String,
        code: String,
        target: String,
    },
    Completed {
        title: String,
        message: Option<String>,
        target: String,
    },
}

/// Full log entry with severity level wrapping a layout.
pub enum LogFormat {
    Error(LogLayout),
    Warn(LogLayout),
    Info(LogLayout),
    Debug(LogLayout),
    Done(LogLayout),
}

impl LogFormat {
    fn level_str(&self) -> &'static str {
        match self {
            LogFormat::Error(_) => "ERROR",
            LogFormat::Warn(_) => "WARN",
            LogFormat::Info(_) => "INFO",
            LogFormat::Debug(_) => "DEBUG",
            LogFormat::Done(_) => "DONE",
        }
    }

    fn level_color(&self) -> &'static str {
        match self {
            LogFormat::Error(_) => COLOR_ERROR,
            LogFormat::Warn(_) => COLOR_WARN,
            LogFormat::Info(_) => COLOR_INFO,
            LogFormat::Debug(_) => COLOR_DEBUG,
            LogFormat::Done(_) => COLOR_DONE,
        }
    }

    fn layout(&self) -> &LogLayout {
        match self {
            LogFormat::Error(l)
            | LogFormat::Warn(l)
            | LogFormat::Info(l)
            | LogFormat::Debug(l)
            | LogFormat::Done(l) => l,
        }
    }

    /// Renders the log entry as a plain (non-colorized) string.
    pub fn render_plain(&self) -> String {
        let level = self.level_str();
        match self.layout() {
            LogLayout::General { title, message, code, target } => {
                format!("{} [{}::{}]\n{}\n{}", code, target, level, title, message)
            }
            LogLayout::Completed { title, message, target } => {
                let suffix = match message {
                    Some(msg) => format!(" {}", msg),
                    None => String::new(),
                };
                format!("[{}::{}] {}{}", target, level, title, suffix)
            }
        }
    }

    /// Renders the log entry with ANSI color codes per the spec palette.
    pub fn render_colored(&self) -> String {
        let level = self.level_str();
        let level_color = self.level_color();

        match self.layout() {
            LogLayout::General { title, message, code, target } => {
                format!(
                    "{}{}{} [{}{}{}::{}{}{}]\n{}\n{}{}{}",
                    COLOR_CODE, code, COLOR_RESET,
                    COLOR_TARGET, target, COLOR_RESET,
                    level_color, level, COLOR_RESET,
                    title,
                    COLOR_DESC, message, COLOR_RESET
                )
            }
            LogLayout::Completed { title, message, target } => {
                let suffix = match message {
                    Some(msg) => format!(" {}", msg),
                    None => String::new(),
                };
                format!(
                    "[{}{}{}::{}{}{}] {}{}",
                    COLOR_TARGET, target, COLOR_RESET,
                    level_color, level, COLOR_RESET,
                    title, suffix
                )
            }
        }
    }

    /// Prints the log to stderr, with color if the terminal supports it.
    pub fn emit(&self) {
        eprintln!("{}\n", self.render_colored());
    }
}

pub struct Logger {
    pub target: String,
    pub platform: String,
}

impl Logger {
    pub fn new(target: &str, platform: &str) -> Self {
        Self {
            target: target.to_string(),
            platform: platform.to_string(),
        }
    }

    fn make_code(&self, id: u16) -> String {
        format!("{}{:03}", self.platform, id)
    }

    pub fn error(&self, id: u16, title: &str, message: &str) {
        LogFormat::Error(LogLayout::General {
            code: self.make_code(id),
            target: self.target.clone(),
            title: title.to_string(),
            message: message.to_string(),
        }).emit();
    }

    pub fn warn(&self, id: u16, title: &str, message: &str) {
        LogFormat::Warn(LogLayout::General {
            code: self.make_code(id),
            target: self.target.clone(),
            title: title.to_string(),
            message: message.to_string(),
        }).emit();
    }

    pub fn info(&self, id: u16, title: &str, message: &str) {
        LogFormat::Info(LogLayout::General {
            code: self.make_code(id),
            target: self.target.clone(),
            title: title.to_string(),
            message: message.to_string(),
        }).emit();
    }

    pub fn debug(&self, id: u16, title: &str, message: &str) {
        LogFormat::Debug(LogLayout::General {
            code: self.make_code(id),
            target: self.target.clone(),
            title: title.to_string(),
            message: message.to_string(),
        }).emit();
    }

    pub fn done(&self, title: &str, message: Option<&str>) {
        LogFormat::Done(LogLayout::Completed {
            target: self.target.clone(),
            title: title.to_string(),
            message: message.map(|m| m.to_string()),
        }).emit();
    }
}

pub fn visual_test() {
    let runtime  = Logger::new("RUNTIME",  "4RT");
    let compiler = Logger::new("COMPILER", "4CP");
    let packager = Logger::new("PACKAGER", "4PM");

    runtime.error(006, "Invalid bytecode", "The bytecode being processed is malformed and cannot be executed further.");
    runtime.warn(102, "Deprecated instruction", "The instruction 'mov8' is deprecated and replaced by 'mv8'.");
    compiler.info(110, "Parsing started", "The compiler has begun parsing the source file.");
    packager.debug(041, "Resolving dependency tree", "Walking the full dependency graph for package 'std@1.x.x@4i'.");
    packager.done("Build completed", Some("All artifacts written to ./dist"));
    compiler.done("Compilation completed successfully", None);
}