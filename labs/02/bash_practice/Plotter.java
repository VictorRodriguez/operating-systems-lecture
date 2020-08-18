import java.io.BufferedReader;
import java.io.FileReader;
import javafx.application.*;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.chart.XYChart.Series;

import java.util.ArrayList;


public class Plotter extends Application {
	@Override
	public void start(Stage stage) throws Exception {
		stage.setTitle("Linux Statistics");
		final CategoryAxis x = new CategoryAxis();
		final NumberAxis y = new NumberAxis();
		final BarChart<String, Number> chart = new BarChart<String, Number>(x, y);
		chart.setTitle("Number of files");
		x.setLabel("File Extension");
		y.setLabel("Files");
		
		BufferedReader reader = new BufferedReader(new FileReader("directories.csv"));
		String line;
		ArrayList<Series<String, Number>> list = new ArrayList<>();
		while((line = reader.readLine()) != null) {
			String[] dir = line.split(",");
			Series<String, Number> series = new Series<>();
			series.setName(dir[0]);
			series.getData().add(new Data<String, Number>("files", Integer.parseInt(dir[1])));
			series.getData().add(new Data<String, Number>(".c", Integer.parseInt(dir[2])));
			series.getData().add(new Data<String, Number>(".h", Integer.parseInt(dir[3])));
			list.add(series);
		}
		
		Scene scene = new Scene(chart, 800, 600);
		chart.getData().addAll(list);
		stage.setScene(scene);
		stage.show();
		
	}
	
	public static void main(String[] args) {
		Application.launch(args);
	}

}
