function addListener(selector, eventType, handler, obj = document) {
	const elements = obj.querySelectorAll(selector);

	Array.from(elements).forEach((element) => {
		element.addEventListener(eventType, handler);
	});
}
