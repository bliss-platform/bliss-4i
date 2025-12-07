import 'dart:io';
import 'package:path/path.dart' as path;

enum CreateTypes {

	project,
	workspace,
	library

}

void create( String name, CreateTypes type ) {

	final directory = Directory( path.join( Directory.current.path, name ) );

	if ( directory.existsSync() ) {
		print("[ERROR] The directory $name already exists.\nAborting create command");
		return;
	}

	//if the directory do not exist
	try {
		directory.createSync(recursive: true);
		print("[SUCCESS] Created project $name");
	} catch(e) {
		print("[ERROR] Unable to create the project.\n${e.toString()}");
	}

}