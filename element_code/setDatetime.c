	//NOTE: If you would like Atmosphere to send this function current UTC time
	//	In the source connector to the Set Datetime element use the following
	//	Source Method: Static
	//	Target Method: Execute
	//	value: new Date().toISOString()
	DS1307_SetISO8601Time(data);
	return;