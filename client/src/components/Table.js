const Table =({data, columns})=>{
return (
    <div>
     <table className="Table">
      <thead>
        <tr>
          {columns.map((column) => (
            <th key={column.Header}>{column.Header}</th>
          ))}
        </tr>
      </thead>
      <tbody>
        {data.map((row) => (
          <tr key={row.id}>
            {columns.map((column) => (
              <td key={column.Header}>
                {column.Cell ? column.Cell({ value: row[column.accessor] }) : row[column.accessor]}
              </td>
            ))}
          </tr>
        ))}
      </tbody>
    </table>
    </div>
)
}
export default Table;