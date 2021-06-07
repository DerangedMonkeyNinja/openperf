// Code generated by go-swagger; DO NOT EDIT.

package cpu_generator

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"
	"net/http"
	"time"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/runtime"
	cr "github.com/go-openapi/runtime/client"
	"github.com/go-openapi/strfmt"
)

// NewGetCPUGeneratorParams creates a new GetCPUGeneratorParams object,
// with the default timeout for this client.
//
// Default values are not hydrated, since defaults are normally applied by the API server side.
//
// To enforce default values in parameter, use SetDefaults or WithDefaults.
func NewGetCPUGeneratorParams() *GetCPUGeneratorParams {
	return &GetCPUGeneratorParams{
		timeout: cr.DefaultTimeout,
	}
}

// NewGetCPUGeneratorParamsWithTimeout creates a new GetCPUGeneratorParams object
// with the ability to set a timeout on a request.
func NewGetCPUGeneratorParamsWithTimeout(timeout time.Duration) *GetCPUGeneratorParams {
	return &GetCPUGeneratorParams{
		timeout: timeout,
	}
}

// NewGetCPUGeneratorParamsWithContext creates a new GetCPUGeneratorParams object
// with the ability to set a context for a request.
func NewGetCPUGeneratorParamsWithContext(ctx context.Context) *GetCPUGeneratorParams {
	return &GetCPUGeneratorParams{
		Context: ctx,
	}
}

// NewGetCPUGeneratorParamsWithHTTPClient creates a new GetCPUGeneratorParams object
// with the ability to set a custom HTTPClient for a request.
func NewGetCPUGeneratorParamsWithHTTPClient(client *http.Client) *GetCPUGeneratorParams {
	return &GetCPUGeneratorParams{
		HTTPClient: client,
	}
}

/* GetCPUGeneratorParams contains all the parameters to send to the API endpoint
   for the get Cpu generator operation.

   Typically these are written to a http.Request.
*/
type GetCPUGeneratorParams struct {

	/* ID.

	   Unique resource identifier

	   Format: string
	*/
	ID string

	timeout    time.Duration
	Context    context.Context
	HTTPClient *http.Client
}

// WithDefaults hydrates default values in the get Cpu generator params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *GetCPUGeneratorParams) WithDefaults() *GetCPUGeneratorParams {
	o.SetDefaults()
	return o
}

// SetDefaults hydrates default values in the get Cpu generator params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *GetCPUGeneratorParams) SetDefaults() {
	// no default values defined for this parameter
}

// WithTimeout adds the timeout to the get Cpu generator params
func (o *GetCPUGeneratorParams) WithTimeout(timeout time.Duration) *GetCPUGeneratorParams {
	o.SetTimeout(timeout)
	return o
}

// SetTimeout adds the timeout to the get Cpu generator params
func (o *GetCPUGeneratorParams) SetTimeout(timeout time.Duration) {
	o.timeout = timeout
}

// WithContext adds the context to the get Cpu generator params
func (o *GetCPUGeneratorParams) WithContext(ctx context.Context) *GetCPUGeneratorParams {
	o.SetContext(ctx)
	return o
}

// SetContext adds the context to the get Cpu generator params
func (o *GetCPUGeneratorParams) SetContext(ctx context.Context) {
	o.Context = ctx
}

// WithHTTPClient adds the HTTPClient to the get Cpu generator params
func (o *GetCPUGeneratorParams) WithHTTPClient(client *http.Client) *GetCPUGeneratorParams {
	o.SetHTTPClient(client)
	return o
}

// SetHTTPClient adds the HTTPClient to the get Cpu generator params
func (o *GetCPUGeneratorParams) SetHTTPClient(client *http.Client) {
	o.HTTPClient = client
}

// WithID adds the id to the get Cpu generator params
func (o *GetCPUGeneratorParams) WithID(id string) *GetCPUGeneratorParams {
	o.SetID(id)
	return o
}

// SetID adds the id to the get Cpu generator params
func (o *GetCPUGeneratorParams) SetID(id string) {
	o.ID = id
}

// WriteToRequest writes these params to a swagger request
func (o *GetCPUGeneratorParams) WriteToRequest(r runtime.ClientRequest, reg strfmt.Registry) error {

	if err := r.SetTimeout(o.timeout); err != nil {
		return err
	}
	var res []error

	// path param id
	if err := r.SetPathParam("id", o.ID); err != nil {
		return err
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}