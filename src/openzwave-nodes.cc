/*
* Gets the neighbors for a node
*/
Handle<Value> OZW::GetNodeNeighbors(const Arguments& args)
{
	HandleScope scope;
	uint8* neighbors;

	uint8_t nodeid = args[0]->ToNumber()->Value();
	uint8 numNeighbors = OpenZWave::Manager::Get()->GetNodeNeighbors(homeid, nodeid, &neighbors);
	Local<Array> o_neighbors = Array::New(numNeighbors);

	for (uint8 nr = 0; nr < numNeighbors; nr++) {
		o_neighbors->Set(Integer::New(nr), Integer::New(neighbors[nr]));
	}

	Local<Value> argv[3];
	argv[0] = String::New("neighbors");
	argv[1] = Integer::New(nodeid);
	argv[2] = o_neighbors;

	MakeCallback(context_obj, "emit", 3, argv);

	return scope.Close(Undefined());
}

Handle<Value> OZW::SwitchAllOn(const Arguments& args) {
	HandleScope scope;

	OpenZWave::Manager::Get()->SwitchAllOn(homeid);

	return scope.Close(Undefined());
}

Handle<Value> OZW::SwitchAllOff(const Arguments& args) {
	HandleScope scope;

	OpenZWave::Manager::Get()->SwitchAllOff(homeid);

	return scope.Close(Undefined());
}

Handle<Value> OZW::SetNodeOn(const Arguments& args) {
	HandleScope scope;
	uint8_t nodeid = args[0]->ToNumber()->Value();
	
	OpenZWave::Manager::Get()->SetNodeOn(homeid, nodeid);

	return scope.Close(Undefined());
}

Handle<Value> OZW::SetNodeOff(const Arguments& args) {
	HandleScope scope;
	uint8_t nodeid = args[0]->ToNumber()->Value();
	
	OpenZWave::Manager::Get()->SetNodeOff(homeid, nodeid);

	return scope.Close(Undefined());
}

/*
* Write a new location string to the device, if supported.
*/
Handle<Value> OZW::SetLocation(const Arguments& args) {
	HandleScope scope;

	uint8_t nodeid = args[0]->ToNumber()->Value();
	std::string location = (*String::Utf8Value(args[1]->ToString()));

	OpenZWave::Manager::Get()->SetNodeLocation(homeid, nodeid, location);

	return scope.Close(Undefined());
}

/*
* Write a new name string to the device, if supported.
*/
Handle<Value> OZW::SetName(const Arguments& args) {
	HandleScope scope;

	uint8_t nodeid = args[0]->ToNumber()->Value();
	std::string name = (*String::Utf8Value(args[1]->ToString()));

	OpenZWave::Manager::Get()->SetNodeName(homeid, nodeid, name);

	return scope.Close(Undefined());
}
