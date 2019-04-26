/**
 * @author v.lugovksy
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.pages.dashboard')
      .controller('DashboardPieChartCtrl', DashboardPieChartCtrl);

  /** @ngInject */
  function DashboardPieChartCtrl($scope, $timeout, baConfig, baUtil) {
    var pieColor = baUtil.hexToRGB(baConfig.colors.defaultText, 0.2);
    $scope.charts = [{
      color: pieColor,
      description: 'Transactions per Hour',
      stats: '4,800',
      icon: 'person',
    }, {
      color: pieColor,
      description: 'Difficulty',
      stats: '24',
      icon: 'money',
    }, {
      color: pieColor,
      description: 'Hash rate',
      stats: '12.1Mhash/s',
      icon: 'face',
    }, {
      color: pieColor,
      description: 'Average Block Time',
      stats: '4m 38s',
      icon: 'refresh',
    }
    ];

    function getRandomArbitrary(min, max) {
      return Math.random() * (max - min) + min;
    }

    function loadPieCharts() {
      $('.chart').each(function () {
        var chart = $(this);
        chart.easyPieChart({
          easing: 'easeOutBounce',
          onStep: function (from, to, percent) {
            $(this.el).find('.percent').text(Math.round(percent));
          },
          barColor: chart.attr('rel'),
          trackColor: 'rgba(0,0,0,0)',
          size: 84,
          scaleLength: 0,
          animation: 2000,
          lineWidth: 9,
          lineCap: 'round',
        });
      });

      $('.refresh-data').on('click', function () {
        updatePieCharts();
      });
    }

    function updatePieCharts() {
      $('.pie-charts .chart').each(function(index, chart) {
        $(chart).data('easyPieChart').update(getRandomArbitrary(55, 90));
      });
    }

    $timeout(function () {
      loadPieCharts();
      updatePieCharts();
    }, 1000);
  }
})();