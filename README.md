# coreTrace
A logging utility for C++.

## Usage
Include the repositry into the libraries.
Then include CoreTrace in the links list and CoreTrace/src/ in the includedirs.
```lua
links {
    CoreTrace
}

includedirs {
    CoreTrace/src/
}
```

## DebugQueue
DebugQueues can track any function calls, with the following metrics.
```cpp
struct DebugEvent {
	int eventID;
	std::string functionName;
	int parentProcess;
	std::vector<Node> functionParameters;
	std::optional<Node> functionReturn;
	std::chrono::time_point<std::chrono::system_clock> functionStart;
	std::chrono::time_point<std::chrono::system_clock> functionEnd;
	std::string functionSuccess;
};
```
Any variables being passed to the function or given as a return value are serialised as `Nodes`.
Nodes track the value, name and any child nodes of a value.
```cpp
struct Node {
	std::vector<Node> childNodes;

	std::string name = "";
	std::string type = "";
	std::string value = ""; 
};
```
