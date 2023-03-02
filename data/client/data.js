async function send(uri, data) {
	return await fetch(`${uri}`, {
		method: "POST",
		headers: {
			"Content-Type": "application/json"
		},
		body: data,
	});
}

async function get(uri) {
	try {
		const response = await fetch(`${uri}`, {
			method: "GET",
		});
		const data = await response.json();
		return data;
	} catch (error) {
		console.error(error);
	}
}

export { send, get };
