import 'dart:io';
import 'package:packager/logger.dart';
import 'package:path/path.dart' as path;

enum CreateTypes {

	project,
	workspace,
	library

}

void create( String name, CreateTypes type ) {

	final directory = Directory( path.join( Directory.current.path, name ) );

	String target = "";
	if ( type == CreateTypes.project ) {
		target = "Project";
	}

	if ( directory.existsSync() ) {
		logger(LogType.error, "011", "Project Creation Failed", "The directory $name already exists.\nAborting create command");
		return;
	}

	//if the directory do not exist
	try {

		directory.createSync(recursive: true);
		logger(LogType.done, "", "Project $name created successfully", "");

	} catch(e) {
		print("[ERROR] Unable to create the project.\n${e.toString()}");
	}

}