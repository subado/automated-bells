function addListener(selector, eventType, handler, obj = document) {
	const elements = obj.querySelectorAll(selector);

	Array.from(elements).forEach((element) => {
		element.addEventListener(eventType, handler);
	});
}

async function sendData(uri, data) {
	return fetch(`${uri}`, {
		method: "POST",
		headers: {
			"Content-Type": "application/json"
		},
		body: data,
	})
}

async function getData(uri) {
	return fetch(`${uri}`, {
		method: "GET",
		headers: {
			"Content-Type": "application/json"
		}
	}).then(response => {
		if (response.ok) {
			return response.json();
		}
	})
}
