using System;
using System.Collections.Generic;
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
    /// Логика взаимодействия для AddSmth.xaml
    /// </summary>
    public partial class AddSmth : Window
    {
        private int form = 0;
        public AddSmth(int form)
        {
            InitializeComponent();
            switch (form)
            {
                default: break;
                case 1:
                    Adress.Visibility= Visibility.Visible;
                    break;
                case 2:
                    Cargo.Visibility = Visibility.Visible;
                    break;
                case 3:
                    Car.Visibility = Visibility.Visible;
                    break;
                case 4:
                    Driver.Visibility = Visibility.Visible;
                    break;
                case 5:
                    Client.Visibility = Visibility.Visible;
                    break;
                case 6:
                    upd.Visibility = Visibility.Visible;
                    break;
                case 7:
                    del.Visibility = Visibility.Visible;
                    break;
            }
        }

        private void addAdress_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "insert into Adress values('"+Country.Text+"','"+City.Text+"','"+Street.Text+"','"+Building.Text+"','"+Postindex.Text+"')";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteReader();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void addCargo_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "insert into Cargo values('" + cargoComp.Text + "','" + cargoWeight.Text + "','" + cargoPack.Text + "','" + cargoHeight.Text + "','" + cargoWidth.Text + "','"+cargoDepth.Text+"','"+cargoStock.Text+"')";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteReader();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void addCar_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "insert into Cars values('" + carReg.Text + "','" + CarMark.Text + "','" + carLift.Text + "','" + isFreeCar.IsChecked + "','" + carCCV.Text +"','"+carHeight.Text+"','"+carWidth.Text+"','"+carDepth.Text+"')";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteReader();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void addDriver_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "insert into Driver values('" + driverSur.Text + "','" + driverName.Text + "','" + driverPatr.Text + "','" + isFreeDriver.IsChecked + "')";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteReader();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void addClient_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "insert into Client values('" + clientName.Text + "','" + clientPhone.Text + "','" + clientEmail.Text + "','" + clientAdres.Text + "')";
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteReader();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void upd1_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "update Adress ";
                if (updCountry.Text != "")
                {
                    sql += "set Country='" + updCountry.Text + "'";
                }
                if (updCity.Text != "")
                {
                    sql += ", City='" + updCity.Text + "'";
                }
                if (updStreet.Text != "")
                {
                    sql += ", Street='" + updStreet.Text + "'";
                }
                if (updBuilding.Text != "")
                {
                    sql += ", Building='" + updBuilding.Text + "'";
                }
                if (updPostindex.Text != "")
                {
                    sql += ", Post_index='" + updPostindex.Text + "'";
                }
                

                sql += " where Adress_id =" + updid.Text;
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteNonQuery();
                    connection.Close();
                }
            }
            this.Close();
        }

        private void delbttn_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(Properties.Settings.Default.connString))
            {
                string sql = "delete from Adress where Adress_id="+delid.Text;
                using (SqlCommand sqlCommand = new SqlCommand(sql, connection))
                {
                    connection.Open();

                    // Run the query by calling ExecuteReader().
                    sqlCommand.ExecuteNonQuery();
                    connection.Close();
                }
            }
            this.Close();
        }
    }
}
