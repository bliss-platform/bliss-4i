Let's consider the following example:

data Entity; //empty data (void) implicator. Takes no space.

action Robot.drive() -> void;
action MurderRobot.kill() -> void;
action CleaningRobot.clean() -> void;

action Animals.poop() -> void;
action Dogs.bark() -> void;
action Cats.meow() -> void;

//I might need a murder robot dog that also cleans but does not poop.

bind (MurderRobot, CleaningRobot, Dogs), Entity as MurderRobotDogBinding {
	fx kill() -> void {
	
	}
	
	fx bark() -> void {
	
	}
	
	fx clean() -> void {
	
	}
}