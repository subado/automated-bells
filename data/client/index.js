fetch("/tables", {
	method: "GET",
	headers: {
		"Content-Type": "application/json"
	}
})
.then(response => {
	if (response.ok) {
		return response.json();
	}
})
.then(data => {
	const list = document.querySelector("#list");

	data.forEach(element => {
		list.innerHTML += `
			<li>
				<input type="button" class="link" value="${element}">
				<input type="radio" name="table" value="${element}">
			</li>`
	});
	addListener("input.link", "click", (event) => {
		button = event.target;
		localStorage.setItem("table", button.value);
		window.location.href = "/table";
	});
});

function updateTime() {
	fetch("/time", {
		method: "GET",
		headers: {
			"Content-Type": "application/json"
		}
	}).then(response => {
		if (response.ok) {
			return response.json();
		}
	}).then(data => {
		document.querySelector("#time").innerHTML = data;
	});
}

updateTime();
setInterval(updateTime, 60 * 1000);
