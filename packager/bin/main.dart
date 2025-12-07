import 'package:packager/create.dart';
import 'package:packager/help.dart';

void main(List<String> args) {

	if ( args.isEmpty ) {
		help();
	} else if ( args.elementAt(0) == 'create' ) {

		if ( args.length != 3 ) {
			print("[ERROR] Insufficient arguments passed to create.");
		}

		CreateTypes dataType = CreateTypes.project; //default
		String creationType = args.elementAt(1);

		if ( creationType == 'workspace' ) {
			dataType = CreateTypes.workspace;
		} else if ( creationType == 'library' ) {
			dataType = CreateTypes.library;
		} else if ( creationType != 'project' ) {

			print('[ERROR] Unrecognized target: $creationType');
			return;

		}

		create(args.elementAt(2), dataType);

	}

}