var startedComponents = componentManager.startedComponents;
var componentsCount = startedComponents.length;
console.log("Started components: " + componentsCount);
for (var i = 0; i < startedComponents.length; ++i) {
    var comp = startedComponents[i];
    console.log(comp.name);
}

var installCmd = serviceLocator.build("InstallComponentsCommand");

// All dependencies for this components also will be installed
installCmd.addDefinitionPath("../org.carousel.demos.NewComponentsDialog.definition");

installCmd.pushToStack();

startedComponents = componentManager.startedComponents;
console.log("\nComponents after installation: " + startedComponents.length);
for (var i = componentsCount; i < startedComponents.length; ++i) {
    var comp = startedComponents[i];
    console.log(comp.name);
}
