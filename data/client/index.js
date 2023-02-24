fetch("/list",
	{
		method: "GET",
		headers:
		{
			"Content-Type": "application/json"
		}
	}).then(response =>
	{
		if (response.ok)
		{
			return response.json();
		}
	}).then(data =>
	{
		const list = document.querySelector("#list");

		data.forEach(element =>
		{
			list.innerHTML += `<li><a href="#">${element}</a></li>`
		});
	})
