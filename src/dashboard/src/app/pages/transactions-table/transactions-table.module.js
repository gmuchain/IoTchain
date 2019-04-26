/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
    'use strict';
  
    angular.module('IotChainDashboard.pages.transactions-table', [])
        .config(routeConfig);
  
    /** @ngInject */
    function routeConfig($stateProvider) {
      $stateProvider
          .state('transactions-table', {
            url: '/transactions-table',
            templateUrl: 'app/pages/transactions-table/transactions-table.html',
            title: 'Transactions',
            controller: 'TransactionsTableCtrl',
            sidebarMeta: {
              icon: 'ion-document-text',
              order: 0,
            },
          })
          .state('transaction_details',{
            url: '/transactions-table/{hash}',
            templateUrl: 'app/pages/widgets/details/transaction-details/transaction-details.html',
            title: 'Transaction Detail',
            controller: 'TransactionDetailCtrl'
          });
    }
  
  })();
  