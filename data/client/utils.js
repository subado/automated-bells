function addListeners(selector, eventType, handler, object = document) {
	const elements = object.querySelectorAll(selector);
	Array.from(elements).forEach((element) => {
		element.addEventListener(eventType, handler);
	});
}

export { addListeners };
