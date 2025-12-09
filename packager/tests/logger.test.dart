import 'package:packager/logger.dart';

void main() {

	logger(LogType.error, "000", "Runtime Crashed", "Unable to start the runtime because of system malfunction.");
	logger(LogType.warn, "001", "Runtime Crashed", "Unable to start the runtime because of system malfunction.");
	logger(LogType.info, "003", "Runtime Crashed", "Unable to start the runtime because of system malfunction.");
	logger(LogType.debug, "004", "Runtime Crashed", "Unable to start the runtime because of system malfunction.");
	logger(LogType.done, "622", "Runtime Crashed", "Unable to start the runtime because of system malfunction.");

}