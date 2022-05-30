function onError(error) {
	console.log(`Error: ${error}`);
}

console.log(`AutoFullscreen Running`);
browser.windows.getAll().then((windowInfoArray) => {
	for (currentWindow of windowInfoArray) {
		browser.windows.update(currentWindow.id, {state: "fullscreen"});
	}
}, onError);