package valueObjects
{

	public class Patient
	{
		public var fName:String;
		public var lName:String;
		public var dob:Number;
		public var lastSeen:Number;
		public var weight:Number;
		public var height:Number;
		public var pic:String;
		public var gender:String;

		public function Patient(fName:String, lName:String, pic:String, gender:String, dob:Number, lastSeen:Number, weight:Number,
								 height:Number)
		{
			this.fName= fName;
			this.lName=lName;
			this.pic=pic;
			this.gender=gender;
			this.dob=dob;
			this.lastSeen=lastSeen;
			this.weight=weight;
			this.height=height;
		}

	}
}