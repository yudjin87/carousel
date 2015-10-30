var scriptCollection = scriptingService.scripts;

/*
var newScriptUnit = scriptCollection.create();
newScriptUnit.scriptText = "var scriptingService = serviceLocator.locate(\"IScriptingService\");\n"
newScriptUnit.scriptText += "var scriptCollection = scriptingService.scripts;\n"
newScriptUnit.scriptText += "var scriptConsole = scriptingService.console;\n"
newScriptUnit.scriptText += "\n"
newScriptUnit.scriptText += "console.log(\"Hello, new world!\");"
newScriptUnit.printed.connect(console.log);

newScriptUnit.run();
*/

// Console
var scriptConsole = scriptingService.console;
scriptConsole.execCommand("console.log(\"Hello, new world!\")");
