/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.pages.components.transaction-details', [])
      .config(routeConfig);

  /** @ngInject */
  function routeConfig($stateProvider) {
    $stateProvider
        .state('transaction-details', {
          url: '/transaction-details',
          templateUrl: 'app/pages/components/transaction-details/transaction-detail.html',
          title: 'TransactionDetail',
          controller: 'TransactionDetailCtrl',
        });
  }

})();
