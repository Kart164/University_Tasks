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
    /// Логика взаимодействия для NavForUser.xaml
    /// </summary>
    public partial class NavForUser : Window
    {
        public NavForUser()
        {
            InitializeComponent();
        }

        private void Watch_adress_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                const string sql = "select * from Adress";
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
                        this.WatchGrid.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void Watch_cargo_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                const string sql = "select * from Cargo";
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
                        this.WatchGrid.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void Watch_Cars_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                const string sql = "select * from Cars";
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
                        this.WatchGrid.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void Watch_Drivers_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                const string sql = "select * from Driver";
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
                        this.WatchGrid.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void Watch_Clients_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                const string sql = "select * from Client";
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
                        this.WatchGrid.ItemsSource = dataTable.DefaultView;

                        // Close the SqlDataReader.
                        dataReader.Close();
                    }
                }
            }
        }

        private void Change_role_Click(object sender, RoutedEventArgs e)
        {
            var wind = new MainWindow();
            wind.Show();
            this.Close();
        }

        private void GetAllInfoFromDelivery_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(1);
            wind.Show();
        }

        private void Search_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(2);
            wind.Show();
        }

        private void rep1_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(4);
            wind.Show();
        }

        private void rep2_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(5);
            wind.Show();
        }

        private void OrederCount_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(6);
            wind.Show();
        }

        private void getLastPos_Click(object sender, RoutedEventArgs e)
        {
            var wind = new otherFunctions(7);
            wind.Show();
        }
    }
}
