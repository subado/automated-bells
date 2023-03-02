export default class HtmlDynamicTable
{
	constructor(table, rowTemplate)
	{
		this.table = document.querySelector(table);
		this.rowTemplate = this.table.querySelector(rowTemplate);
		this.body = this.table.querySelector("tbody");
	}

	addRow(prevRow)
	{
		const row = this.rowTemplate.content.cloneNode(true)

		const buttons = row.querySelectorAll("button");

		if (buttons != undefined)
		{
			buttons.forEach(button =>
			{
				this.addButtonListener(button, this);
			});
		}

		if (prevRow != undefined)
		{
			this.body.insertBefore(row, this.body.rows[prevRow.rowIndex]);
		}
		else
		{
			this.body.appendChild(row);
		}
	}

	removeRow(row)
	{
		if (this.body.rows.length > 1)
		{
			this.body.removeChild(row);
		}
	}

	handleAddButton(event)
	{
		this.addRow(getRowOfButton(event.currentTarget));
	}

	handleRemoveButton(event)
	{
		this.removeRow(getRowOfButton(event.currentTarget));
	}

	addButtonListener(button)
	{
		button.classList.forEach(className =>
		{
			let handler;
			switch (className)
			{
			case "add-button":
				handler = this.handleAddButton.bind(this);
				break;
			case "remove-button":
				handler = this.handleRemoveButton.bind(this);
				break;
			}
			
			if (handler != undefined)
			{
				button.addEventListener("click", handler);
			}
		});
	}
}

function getRowOfButton(button)
{
	return getParentElement(button, "tr");
}

function getParentElement(element, parent)
{
	while (element.localName != parent)
	{
		element = element.parentElement;
	}

	return element;
}
