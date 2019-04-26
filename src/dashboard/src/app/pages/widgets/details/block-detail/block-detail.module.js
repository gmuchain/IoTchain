/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
    'use strict';
  
    angular.module('IotChainDashboard.pages.components.block-detail', [])
        .config(routeConfig);
  
    /** @ngInject */
    function routeConfig($stateProvider) {
      $stateProvider
          .state('block-detail', {
            url: '/block-detail',
            templateUrl: 'app/pages/components/block-detail/block-detail.html',
            title: 'BlockDetail',
            controller: 'BlockDetailCtrl',
          })
          .state('transaction_details',{
            url: '/transactions-table/{hash}',
            templateUrl: 'app/pages/components/transaction-details/transaction-details.html',
            title: 'Transaction Detail',
            controller: 'TransactionDetailCtrl'
          });
    }
  
  })();
  