/**
 * @author v.lugovksy
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.theme.components')
      .directive('pageTop', pageTop);

  /** @ngInject */
  function pageTop() {
    return {
      restrict: 'E',
      templateUrl: 'app/theme/components/pageTop/pageTop.html',
      controller: 'PageTopCtrl',
      link: function($scope) {
        $scope.startSearch = function(){
          console.log("test2");
        }
      }
    };
  }

})();