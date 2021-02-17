using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace DeliveryApp1
{
    /// <summary>
    /// Логика взаимодействия для otherFunctions.xaml
    /// </summary>
    public partial class otherFunctions : Window
    {
        public otherFunctions(int type)
        {
            InitializeComponent();
            switch (type)
            {
                default:break;
                case 1:
                    getInfoGrid.Visibility = Visibility.Visible;
                    using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
                    {
                        const string sql = "select * from Delivery";
                        using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                        {
                            connection.Open();

                            // Run the query by calling ExecuteReader().
                            using (SqlDataReader dataReader = sqlCommand.ExecuteReader())
                            {
                                // Create a data table to hold the retrieved data.
                                DataTable dataTable = new DataTable();

                                // Load the data from SqlDataReader into the data table.
                                dataTable.Load(dataReader);


                                // Display the data from the data table in the data grid view.
                                this.DeliveryTable.ItemsSource = dataTable.DefaultView;

                                // Close the SqlDataReader.
                                dataReader.Close();
                            }
                        }
                    }
                    break;
                case 2:
                    HardSearch.Visibility = Visibility.Visible;
                    break;
                case 3:
                    addViewGrid.Visibility = Visibility.Visible;
                    break;
                case 4:
                    rep1.Visibility = Visibility.Visible;
                    break;
                case 5:
                    rep2.Visibility = Visibility.Visible;
                    break;
                case 6:
                    rep3.Visibility = Visibility.Visible;
                    break;
                case 7:
                    rep4.Visibility = Visibility.Visible;
                    break;
            }
        }

        private void DeliveryTable_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "";
                var datarow = (DataRowView)DeliveryTable.SelectedItem;
                int index = DeliveryTable.CurrentCell.Column.DisplayIndex;
                string info = datarow.Row.ItemArray[index].ToString();
                if (DeliveryTable.CurrentColumn.Header.Equals("Stock"))
                {
                    
                    sql = "select Stock_id,b.Adress_id,b.Country,b.City,b.Street,b.Building,b.Post_index from Stock as a join Adress as b on a.Stock_adress=b.Adress_id where a.Stock_id="+info;
                    var command = new SqlCommand(sql, connection);
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = command.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.getInfo.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                } else if (DeliveryTable.CurrentColumn.Header.Equals("Car_Reg_number")){
                    sql = "select * from Cars where Reg_number='" +info+"'";
                    var command = new SqlCommand(sql, connection);
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = command.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.getInfo.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
                else if (DeliveryTable.CurrentColumn.Header.Equals("Driver_id")) {
                    sql = "select * from Driver where Driver_id=" + info;
                    var command = new SqlCommand(sql, connection);
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = command.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.getInfo.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
                else if (DeliveryTable.CurrentColumn.Header.Equals("Order_id")) {
                    sql = "select * from Company_order where Order_id=" + info;
                    var command = new SqlCommand(sql, connection);
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = command.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.getInfo.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
                else if (DeliveryTable.CurrentColumn.Header.Equals("Last_apperance_adress"))
                {
                    sql = "select * from Adress where Adress_id=" + info;
                    var command = new SqlCommand(sql, connection);
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = command.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.getInfo.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
                else { }


            }
        }

        private void search_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "select a.Delivery_id,c.Order_id, c.Cargo,c.Stock,c.Company,c.Date_of_receiving,c.Destination,c.Bill from Delivery as a join Company_order as c on c.Order_id = a.Order_id join Client as d on c.Company = d.Company_id where d.Name = '"+CompName.Text+"'";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = sqlCommand.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.orders.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void addview_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                connection.Open();
                string sql = "insert into Free_Cars_report values('"+Reg.Text+"','"+Mark.Text+"',"+lift.Text+",1,"+cvv.Text+","+height.Text+","+width.Text+","+depth.Text+")";
                var sqlCommand = new SqlCommand(sql, connection);
                sqlCommand.ExecuteNonQuery();
                sql = "Select * from Free_Cars_report";
                sqlCommand = new SqlCommand(sql, connection);

                    // Run the query by calling ExecuteReader().
                    using (SqlDataReader dataReader = sqlCommand.ExecuteReader())
                    {
                        // Create a data table to hold the retrieved data.
                        DataTable dataTable = new DataTable();

                        // Load the data from SqlDataReader into the data table.
                        dataTable.Load(dataReader);


                        // Display the data from the data table in the data grid view.
                        this.view.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                connection.Close();
            }
        }

        private void calculate_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                connection.Open();
                SqlCommand command = new SqlCommand("Profit_acc", connection);
                command.Parameters.Add(new SqlParameter("@acc_num", SqlDbType.VarChar,20));
                command.Parameters["@acc_num"].Value = acc.Text;
                command.Parameters.Add(new SqlParameter("@date_start", SqlDbType.Date));
                command.Parameters["@date_start"].Value=dataStart.Text;
                command.Parameters.Add(new SqlParameter("@date_end", SqlDbType.Date));
                command.Parameters["@date_end"].Value=endDate.Text;
                command.Parameters.Add(new SqlParameter("@sum",SqlDbType.Decimal));
                command.Parameters["@sum"].Value = 0;
                command.Parameters["@sum"].Direction = ParameterDirection.Output;
                command.CommandType = CommandType.StoredProcedure;
                command.ExecuteNonQuery();

                var parsedProf = (decimal)command.Parameters["@sum"].Value;
                res.Text = parsedProf.ToString();
                connection.Close();
            }
        }

        private void calculate1_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                connection.Open();
                SqlCommand command = new SqlCommand("Profit_all", connection);
                command.Parameters.Add(new SqlParameter("@date_start", SqlDbType.Date));
                command.Parameters["@date_start"].Value = dataStart1.Text;
                command.Parameters.Add(new SqlParameter("@date_end", SqlDbType.Date));
                command.Parameters["@date_end"].Value = endDate1.Text;
                command.Parameters.Add(new SqlParameter("@sum", SqlDbType.Decimal));
                command.Parameters["@sum"].Value = 0;
                command.Parameters["@sum"].Direction = ParameterDirection.Output;
                command.CommandType = CommandType.StoredProcedure;
                command.ExecuteNonQuery();

                var parsedProf = (decimal)command.Parameters["@sum"].Value;
                res1.Text = parsedProf.ToString();
                connection.Close();
            }
        }

        private void calc2_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                connection.Open();
                SqlCommand command = new SqlCommand("OrderCount", connection);
                command.Parameters.Add(new SqlParameter("@company", SqlDbType.VarChar, 100));
                command.Parameters["@company"].Value = companyCount.Text;
                command.Parameters.Add(new SqlParameter("@count", SqlDbType.Int));
                command.Parameters["@count"].Value = 0;
                command.Parameters["@count"].Direction = ParameterDirection.Output;
                command.CommandType = CommandType.StoredProcedure;
                command.ExecuteNonQuery();

                var parsedProf = (int)command.Parameters["@count"].Value;
                res2.Text = parsedProf.ToString();
                connection.Close();
            }
        }

        private void track_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                connection.Open();
                SqlCommand command = new SqlCommand("getLastPosition", connection);
                command.Parameters.Add(new SqlParameter("@order", SqlDbType.BigInt));
                command.Parameters["@order"].Value = Order_id.Text;
                command.Parameters.Add(new SqlParameter("@info", SqlDbType.VarChar,250));
                command.Parameters["@info"].Direction = ParameterDirection.Output;
                command.CommandType = CommandType.StoredProcedure;
                command.ExecuteNonQuery();
                res3.Text = command.Parameters["@info"].Value.ToString();
                connection.Close();
            }
        }
    }
}
